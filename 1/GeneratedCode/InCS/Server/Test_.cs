
using System;
using org.company.some_namespace;
using org.company.some_namespace.Server;
using org.unirail;
using System.Diagnostics;
using System.Linq;
using Cursor = org.unirail.AdHoc.Pack.Cursor;
using Pack = org.unirail.AdHoc.Pack;
using Lib = org.unirail.AdHoc;
using System.IO;
using System.Text;

namespace org.unirail
{
    public struct Test
    {





        class TestChannel : Stream
        {
            public override void Flush() { }
            public override long Seek(long offset, SeekOrigin origin) { throw new NotSupportedException(); }
            public override void SetLength(long value) { throw new NotSupportedException(); }
            public override bool CanRead { get { return true  ; } }
            public override bool CanWrite { get { return true; } }
            public override bool CanSeek => false;
            public override long Length => throw new NotSupportedException();

            public override long Position
            {
                get => throw new NotSupportedException();
                set => throw new NotSupportedException();
            }

            private bool is_advanced = false;

            public TestChannel Adv
            {
                get
                {
                    is_advanced = true;
                    return this;
                }
            }

            public TestChannel Std
            {
                get
                {
                    is_advanced = false;
                    return this;
                }
            }

            public TestChannel()
            {
                receiver = new Receiver(this);
                receiverAdv = new ReceiverAdv(this);
                transmitter = new Transmitter(this);
                transmitterAdv = new TransmitterAdv(this);
            }

            protected internal  Pack.Meta dispatch(int id, Pack pack)
            {
                switch(id)
                {
                    case 0:
                        if(pack == null) return org.company.some_namespace.Server.FirstPack.pack_.meta;
                        onFirstPack();
                        return null;
                }
                return null;
            }

            public override void Write(byte[] src, int offset, int bytes)
            {
                if(is_advanced)
                    receiverAdv.BytesIntoPacks(src, offset, bytes);
                else
                    receiver.BytesIntoPacks(src, offset, bytes);
            }

            class Receiver : Lib.Channel.Receiver
            {
                readonly TestChannel ch;
                public Receiver(TestChannel ch): base(1, 0) { this.ch = ch; }
                protected internal override Pack.Meta dispatch(int id, Pack pack)  { return ch.dispatch(id, pack) ;}
            }
            readonly Receiver receiver;

            class ReceiverAdv : Lib.Channel.Receiver.Advanced
            {
                readonly TestChannel ch;
                public ReceiverAdv(TestChannel ch): base(1, 0) { this.ch = ch; }
                protected internal override Pack.Meta dispatch(int id, Pack pack)  { return ch.dispatch(id, pack); }
            }
            readonly ReceiverAdv receiverAdv;


            Pack sendingPack = null;

            public override int Read(byte[] dst, int offset, int bytes)
            {
                return is_advanced ? transmitterAdv.PacksIntoBytes(dst, offset, bytes) : transmitter.PacksIntoBytes(dst, offset, bytes);
            }

            class Transmitter : Lib.Channel.Transmitter
            {
                readonly TestChannel ch;
                public  Transmitter(TestChannel ch): base(1, 0) { this.ch = ch; }
                protected internal override Pack pullSendingPack()
                {
                    var ret = ch.sendingPack;
                    ch.sendingPack = null;
                    return ret;
                }
            }
            readonly Transmitter transmitter;

            class TransmitterAdv : Lib.Channel.Transmitter.Advanced
            {
                readonly TestChannel ch;
                public  TransmitterAdv(TestChannel ch): base(1, 0) { this.ch = ch; }
                protected internal override Pack pullSendingPack()
                {
                    var ret = ch.sendingPack;
                    ch.sendingPack = null;
                    return ret;
                }
            }
            readonly TransmitterAdv transmitterAdv;

            public  bool sendFirstPack()
            {
                if(sendingPack != null) return false;
                sendingPack = org.company.some_namespace.Server. FirstPack.pack_;
                return  true;
            }


        }


        public static void onFirstPack() {Debug.Print("FirstPack \n"); }


        public class ClientServerLink_test: ClientServerLink
        {
            protected override void onFirstPack()
            {
                org.unirail.Test. onFirstPack();
            }

        }

        public static void Main(string[] args)
        {
            var cur = Config.Cursor();
            var cur_dst = Config.Cursor();
            var TestChannel_instance = new TestChannel();
            var ClientServerLink_instance = new ClientServerLink_test();
            Debug.Print("-------------------- FirstPack -------------------------");
            if(TestChannel_instance.sendFirstPack()) TestChannel_instance.Adv.CopyTo(ClientServerLink_instance);
            else throw new SystemException("error AD_HOC_FAILURE_SENDING_QUEUE_OVERFLOW");
        }
    }
}
