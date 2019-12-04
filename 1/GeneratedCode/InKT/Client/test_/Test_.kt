
package test_
import demo_.*
import java.util.*
import kotlin.experimental.*
import org.company.some_namespace.Client.*
import org.unirail.AdHoc
import org.unirail.AdHoc.*
import org.unirail.AdHoc.Pack.Cursor

class TestChannel : AdHoc.Channel() {

    var sendingPack: AdHoc.Pack? = null
    val transmitter: java.io.InputStream = object : Transmitter(1, 0) {
        override fun pullSendingPack(): Pack? {
            val ret = sendingPack
            sendingPack = null
            return ret
        }
    }
    val transmitterAdv: java.io.InputStream = object : Transmitter.Advanced(1, 0) {
        override fun pullSendingPack(): Pack? {
            val ret = sendingPack
            sendingPack = null
            return ret
        }
    }

    val receiver: java.io.OutputStream = object : Receiver(1, 0) {
        override fun dispatch(id: Int, pack: Pack?): Pack.Meta? { return test_dispatch(id, pack) }
    }
    val receiverAdv: java.io.OutputStream = object : Receiver.Advanced(1, 0) {
        override fun dispatch(id: Int, pack: Pack?): Pack.Meta? { return test_dispatch(id, pack) }
    }

    fun test_dispatch(id: Int, pack: Pack?): Pack.Meta? {
        when (id) {
            0 -> pack?.let { onFirstPack() } ?: return FirstPack.pack.meta
        }
        return null
    }

    fun sendFirstPack(): Boolean {
        if (sendingPack != null) return false
        sendingPack = FirstPack.pack
        return true
    }
}

fun onFirstPack() { println("FirstPack \n") }

class ClientServerLink_test : ClientServerLink() {
    var sendingPack: Pack? = null
    override fun pullSendingPack(): Pack? {
        val ret = sendingPack
        sendingPack = null
        return ret
    }
    override fun pushSendingPack(pack: AdHoc.Pack): Boolean {
        if (sendingPack != null) return false

        sendingPack = pack
        return true
    }
}

// By default, assertions are disabled at runtime. Two command-line switches allow you to selectively enable or disable assertions.
// To enable assertions at various granularities, use the -enableassertions, or -ea, switch.
// To disable assertions at various granularities, use the -disableassertions, or -da,

fun main() {
    val cur = Cursor()
    val cur_dst = Cursor()

    val buff = ByteArray(1024)
    fun transmission(src: java.io.InputStream, dst: java.io.OutputStream) {
        try {
            while (true) {
                val bytes = src.read(buff, 0, buff.size)
                if (bytes < 1) break
                dst.write(buff, 0, bytes)
            }
        } catch (e: java.io.IOException) {
            e.printStackTrace()
            assert(false)
        }
    }
    val TestChannel_instance = TestChannel()
    val ClientServerLink_instance = ClientServerLink_test()

    println("-------------------- FirstPack -------------------------")

    if (ClientServerLink_instance.sendFirstPack()) transmission(ClientServerLink_instance.transmitter, TestChannel_instance.receiverAdv)
    else throw RuntimeException("error BBOX_FAILURE_SENDING_QUEUE_OVERFLOW")
}
