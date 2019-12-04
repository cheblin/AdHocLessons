
package demo_

import org.company.some_namespace.Client.*
import java.util.concurrent.ConcurrentLinkedQueue
import kotlin.experimental.*
import org.unirail.AdHoc

var some_Int = 0.toInt()

fun onFirstPack() {}
class ClientServerLink_demo : ClientServerLink() {
    val sendingPacks = ConcurrentLinkedQueue< AdHoc.Pack >()
    override fun pushSendingPack(pack: AdHoc.Pack): Boolean { return sendingPacks.add(pack) }
    override fun pullSendingPack(): AdHoc.Pack? { return sendingPacks.poll() }
}

fun main() {
    val buff = ByteArray(1024)
    var bytes_out = 0
    val cur = Cursor()

    val ClientServerLink_instance = ClientServerLink_demo()

    if (! ClientServerLink_instance.sendFirstPack())
        throw RuntimeException("error BBOX_FAILURE_SENDING_QUEUE_OVERFLOW")

    bytes_out = ClientServerLink_instance.transmitter.read(buff) // sending out packs
}
