
use ad_hoc_gen::org::company::some_namespace as host;
use host::Client as packs;
use ad_hoc_gen::sys;
use std::sync::mpsc::*;
use host::ClientServerLink;

#[no_mangle]
pub extern "C" fn host_event(place: u32, receiver: *mut sys::Receiver, transmitter: *mut sys::Transmitter, pack: *mut sys::Pack, event: sys::HOST_EVENT) {
	unsafe {
		sys::free_pack(pack);
	}
}
const some_usize: usize = 0_usize;

use host::ClientServerLink::ITransmitter as ClientServerLink_ITransmitter;
pub struct ClientServerLink_transmitter {
	pub transmitter:   sys::Transmitter,
	pub sending_queue: (Sender<*mut sys::Pack>, Receiver<*mut sys::Pack>),
}

impl ClientServerLink_transmitter {
	pub fn new() -> ClientServerLink_transmitter { ClientServerLink_transmitter { transmitter: <ClientServerLink_transmitter as ClientServerLink::ITransmitter>::new(), sending_queue: channel::<*mut sys::Pack>() } }
}

impl host::ClientServerLink::ITransmitter for ClientServerLink_transmitter {
	unsafe extern "C" fn dequeue(dst: *mut sys::Transmitter) -> *mut sys::Pack {
		let self_: &mut Self = ad_hoc_gen::sys::self_by_field_ptr!(dst, transmitter);

		if let Ok(mut pack) = self_.sending_queue.1.try_recv() {
			return pack;
		}
		return std::ptr::null_mut();
	}
	fn queue(&mut self, pack: *mut sys::Pack) -> Result<(), *mut sys::Pack> {
		if self.sending_queue.0.send(pack).is_err() {
			return Err(pack);
		}
		Ok(())
	}
	fn get_transmitter(&mut self) -> &mut sys::Transmitter { &mut self.transmitter }
}

impl ::std::io::Read for ClientServerLink_transmitter {
	#[inline(always)]
	fn read(&mut self, dst: &mut [u8]) -> Result<usize, ::std::io::Error> { self.packs_into_bytes(dst) }
}
