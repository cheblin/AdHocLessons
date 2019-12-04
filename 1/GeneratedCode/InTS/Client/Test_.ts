//const assert = require('assert').strict; //https://nodejs.org/api/assert.html

import { org as _org } from './AdHoc';
import _Lib = _org.unirail.AdHoc;
import _Pack = _Lib.Pack;
import _Cursor = _Pack.Cursor;

import { org as _bbox } from './Client';
import _Config = _bbox.unirail.AdHoc.Config;

import { org as _gen } from './Client';
import _Host_root = _gen.company.some_namespace;
import _Host = _gen.company.some_namespace.Client;

export namespace org.unirail {
    export namespace Test_ {
        import _Test = org.unirail.Test_;

        function assertFloatEqual(a: any, b: any) {
            if (a === b) return;

            if (a instanceof Array && b instanceof Array) {
                if (a.length !== b.length) throw new Error(`a.length=${a.length} !== b.length=${b.length}`);
                for (let i = 0, max = a.length; i < max; i++) if (Math.fround(a[i]) !== Math.fround(b[i])) throw new Error(`a[${i}]=${a} !== b[${i}]=${b}`);
                return;
            }
            let A = a[Symbol.iterator]?.();
            let B = b[Symbol.iterator]?.();
            if (A && B)
                for (let i = 0; ; i++) {
                    const A_next = A.next();
                    const B_next = B.next();
                    if (A_next.done === B_next.done)
                        if (A_next.done) return;
                        else if (Math.fround(A_next.value) === Math.fround(B_next.value)) continue;

                    throw new Error(`At index = ` + i + '\nA.done = ' + A_next.done + '\tA.value = ' + A_next.value + '\nB.done = ' + B_next.done + '\tB.value = ' + B_next.value);
                }

            if (Math.fround(a) !== Math.fround(b)) throw new Error(`a=${a} !== b=${b}`);
        }

        function assertEqual(a: any, b: any) {
            if (a === b) return;

            if (a instanceof Array && b instanceof Array) {
                if (a.length !== b.length) throw new Error(`a.length=${a.length} !== b.length=${b.length}`);
                for (let i = 0, max = a.length; i < max; i++) if (a[i] !== b[i]) throw new Error(`a[${i}]=${a} !== b[${i}]=${b}`);
                return;
            }

            let A = a[Symbol.iterator]?.();
            let B = b[Symbol.iterator]?.();
            if (A && B)
                for (let i = 0; ; i++) {
                    const A_next = A.next();
                    const B_next = B.next();
                    if (A_next.done === B_next.done)
                        if (A_next.done) return;
                        else if (A_next.value === B_next.value) continue;

                    throw new Error(`At index = ` + i + '\nA.done = ' + A_next.done + '\tA.value = ' + A_next.value + '\nB.done = ' + B_next.done + '\tB.value = ' + B_next.value);
                }

            throw new Error(`a=${a} !== b=${b}`);
        }

        namespace TestChannel {
            function dispatch(id: number, pack: _Pack): _Pack.Meta | null {
                switch (id) {
                    case 0:
                        if (!pack) return _Host.FirstPack.pack_.meta;
                        onFirstPack();
                        return null;
                }
                return null;
            }
            class Receiver extends _Lib.Channel.Receiver {
                constructor() {
                    super(1, 0);
                }
                dispatch(id: number, pack: _Pack): _Pack.Meta | null {
                    return dispatch(id, pack);
                }
            }

            class ReceiverAdv extends _Lib.Channel.Receiver.Advanced {
                constructor() {
                    super(1, 0);
                }
                dispatch(id: number, pack: _Pack): _Pack.Meta | null {
                    return dispatch(id, pack);
                }
            }
            export const receiverStd = new Receiver();
            export const receiverAdv = new ReceiverAdv();

            let sendingPack: _Pack | null = null;

            class Transmitter extends _Lib.Channel.Transmitter {
                constructor() {
                    super(1, 0);
                }
                pullSendingPack(): _Pack | null {
                    let ret = sendingPack;
                    sendingPack = null;
                    return ret;
                }
            }
            class TransmitterAdv extends _Lib.Channel.Transmitter.Advanced {
                constructor() {
                    super(1, 0);
                }
                pullSendingPack(): _Pack | null {
                    let ret = sendingPack;
                    sendingPack = null;
                    return ret;
                }
            }
            export const transmitterStd = new Transmitter();
            export const transmitterAdv = new TransmitterAdv();

            export function sendFirstPack(): boolean {
                if (sendingPack) return false;
                sendingPack = _Host.FirstPack.pack_;
                return true;
            }
        }

        export function onFirstPack() {
            console.info('FirstPack \n');
        }

        class ClientServerLink_test extends _Host_root.ClientServerLink {
            sendingPack: _Pack | null = null;
            pullSendingPack(): _Pack | null {
                let pack = this.sendingPack;
                this.sendingPack = null;
                return pack;
            }
            pushSendingPack(pack: _Pack): boolean {
                if (this.sendingPack) return false;
                this.sendingPack = pack;
                return true;
            }
        }

        export function Main() {
            let cur = _Config.Cursor();
            let cur_dst = _Config.Cursor();
            let ClientServerLink_instance = new ClientServerLink_test();

            console.info('-------------------- FirstPack -------------------------');

            if (ClientServerLink_instance.sendFirstPack()) _Lib.Channel.bytes_transfer(ClientServerLink_instance.transmitter, TestChannel.receiverAdv);
            else throw new Error('error BBOX_FAILURE_SENDING_QUEUE_OVERFLOW');
        }
    }
}
org.unirail.Test_.Main();
