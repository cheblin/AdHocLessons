import { org as _org } from './AdHoc';
import _Lib = _org.unirail.AdHoc;
import _Pack = _Lib.Pack;
import _Cursor = _Pack.Cursor;

export namespace org.company.some_namespace {
    export namespace Client {
        export namespace FirstPack {
            export const pack_ = new _Pack(new _Pack.Meta(0));
        }
    }
    import _Host = org.company.some_namespace.Client;

    export abstract class ClientServerLink {
        public readonly transmitter = new ClientServerLink.Transmitter(this);
        public abstract pullSendingPack(): _Pack | null;
        public abstract pushSendingPack(pack: _Pack): boolean;
        public sendFirstPack(): boolean {
            return this.pushSendingPack(_Host.FirstPack.pack_);
        }

        public send(src): boolean {
            if (!src.data_.bytes) return false;
            let pack = src.data_.unwrap();
            if (this.pushSendingPack(pack)) return true;
            src.data_.wrap(pack);
            return false;
        }
    }
    export namespace ClientServerLink {
        export class Transmitter extends _Lib.Channel.Transmitter.Advanced {
            constructor(public readonly ch: ClientServerLink) {
                super(1, 0);
            }
            public pullSendingPack(): _Pack | null {
                return this.ch.pullSendingPack();
            }
        }
    }
} // namespace  org.company.some_namespace
export namespace org.unirail.AdHoc {
    import _Host = org.company.some_namespace.Client;

    export namespace Config {
        export function Cursor(): _Cursor {
            return new _Cursor(1, 2);
        }
    }
}
