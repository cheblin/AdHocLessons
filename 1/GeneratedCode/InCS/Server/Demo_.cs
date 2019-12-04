
using System;

using org.company.some_namespace;
using org.company.some_namespace.Server;
using System.Collections.Generic;
using org.unirail;
using Cursor = org.unirail.AdHoc.Pack.Cursor;
using Pack = org.unirail.AdHoc.Pack;
using Lib = org.unirail.AdHoc;

namespace org.unirail
{
    public struct Demo
    {

        static   int  some_int    = (int)0 ;

        public static void onFirstPack() {}


        public class ClientServerLink_demo: ClientServerLink
        {
            protected override void onFirstPack()
            {
                on_FirstPack(this, null);
            }
            public  event Pack.Handler< ClientServerLink_demo, object > on_FirstPack;

        }

        public static void Main2(string[] args)
        {
            var cur = Config.Cursor();
            var buff = new byte[512];
            int bytes_out = 0;
            var ClientServerLink_instance = new  ClientServerLink_demo();
            ClientServerLink_instance.on_FirstPack += (ch, pack) => onFirstPack();
            ClientServerLink_instance.Write(buff, 0, buff.Length);// receiving packs
        }
    }
}
