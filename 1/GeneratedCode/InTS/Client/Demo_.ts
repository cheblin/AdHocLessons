import { org as _org } from './AdHoc';
import _Lib = _org.unirail.AdHoc;
import _Pack = _Lib.Pack;
import _Cursor = _Pack.Cursor;

import { org as _ad_hoc } from './Client';
import _Config = _ad_hoc.unirail.AdHoc.Config;

import { org as _gen } from './Client';
import _Host_root = _gen.company.some_namespace;
import _Host = _gen.company.some_namespace.Client;

export namespace org.unirail {
    export namespace Demo_ {
        let some_string = 'null';
        let some_boolean = true;
        let some_number = 0;
        let some_numbers: number[] = [];

        type Handler<Channel, Pack> = (src: Channel, pack: Pack) => void;

        export function onFirstPack() {}

        class ClientServerLink_demo extends _Host_root.ClientServerLink {
            readonly sendingPacks = new Array<_Pack>(5);
            public pullSendingPack(): _Pack | null {
                return this.sendingPacks.shift()!;
            }
            public pushSendingPack(pack: _Pack): boolean {
                this.sendingPacks.push(pack);
                return true;
            }
        }

        export function Main() {
            let cur = _Config.Cursor();
            let buff = new Uint8Array(new ArrayBuffer(512));
            let bytes_out = 0;

            let ClientServerLink_instance = new ClientServerLink_demo();

            if (!ClientServerLink_instance.sendFirstPack()) throw new Error('error AD_HOC_FAILURE_SENDING_QUEUE_OVERFLOW');

            bytes_out = ClientServerLink_instance.transmitter.packs_into_bytes(buff, 0, buff.byteLength); // sending packs
        }
    }
}
