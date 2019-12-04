
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using org.unirail;
using Cursor = org.unirail.AdHoc.Pack.Cursor;
using Field = org.unirail.AdHoc.Pack.Meta.Field;
using Pack = org.unirail.AdHoc.Pack;
using Lib  = org.unirail.AdHoc;
using System.IO;
using org.company.some_namespace.Server;




namespace  org.company.some_namespace
{
    namespace Server
    {

        public struct FirstPack
        {
            internal static readonly Pack pack_ = new Pack(new Pack.Meta(0));
        }

    }

    public abstract class ClientServerLink : Stream
    {
        public override void Flush() { }
        public override long Seek(long offset, SeekOrigin origin) { throw new NotSupportedException(); }
        public override void SetLength(long value) { throw new NotSupportedException(); }
        public override bool CanRead { get { return false  ; } }
        public override bool CanWrite { get { return true; } }
        public override bool CanSeek => false;
        public override long Length => throw new NotSupportedException();

        public override long Position
        {
            get => throw new NotSupportedException();
            set => throw new NotSupportedException();
        }

        public ClientServerLink()
        {
            receiver = new Receiver(this);
        }


        public override void Write(byte[] src, int offset, int bytes) { receiver.BytesIntoPacks(src, offset, bytes); }
        class Receiver : Lib.Channel.Receiver.Advanced
        {
            readonly ClientServerLink ch;
            public Receiver(ClientServerLink ch): base(1, 0) { this.ch = ch; }

            protected internal override Pack.Meta dispatch(int id, Pack pack)
            {
                switch(id)
                {
                    case 0 :
                        if(pack == null)return FirstPack.pack_.meta ;
                        ch.onFirstPack();
                        break;
                }
                return null;
            }
        }
        readonly Receiver receiver;
        protected abstract void onFirstPack();


        public override int Read(byte[] buffer, int offset, int count) { throw new NotImplementedException(); }


    }

}
namespace org.unirail
{
    using org.company.some_namespace.Server;

    public struct Config
    {
        public static Cursor Cursor() { return new Cursor(null, 1, 2);}

    }
}
