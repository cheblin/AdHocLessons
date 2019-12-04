
package org.company.some_namespace.Client

import java.util.*
import kotlin.experimental.*
import org.company.some_namespace.Client.util_.*
import org.unirail.AdHoc.*
import org.unirail.AdHoc.Pack.Cursor
import org.unirail.AdHoc.Pack.Meta
fun Cursor(): Cursor {
    return Cursor(null, 1, 2)
}

object FirstPack {
    val pack = Pack(Meta(0))
}

abstract class ClientServerLink {

    abstract fun pushSendingPack(pack: Pack): Boolean
    abstract fun pullSendingPack(): Pack?

    val transmitter: java.io.InputStream = object : Channel.Transmitter.Advanced(1, 0) {
        override fun pullSendingPack(): Pack? { return this@ClientServerLink.pullSendingPack() }
    }
    fun sendFirstPack(): Boolean {
        return pushSendingPack(FirstPack.pack)
    }
}
