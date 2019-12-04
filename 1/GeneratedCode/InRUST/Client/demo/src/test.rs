
use ad_hoc_gen::org::company::some_namespace as host;
use host::Client as packs;
use ad_hoc_gen::sys;
use std::mem::transmute;
use std::sync::mpsc::*;
use host::ClientServerLink;

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

pub mod ADV_ {
	use ad_hoc_gen::org::company::some_namespace as host;
	use host::Client as packs;
	use ad_hoc_gen::sys;
	use std::mem::transmute;

	pub trait IReceiver {
		/**
			* Getting reference to customer receiver by reference to sys::Receiver inside it. Mostly used self_by_field_ptr! macros
			**/
		unsafe fn into_self<'a>(receiver: *mut sys::Receiver) -> &'a mut Self;
		/**
			* Get internal sys::Receiver from Customer receiver
			**/
		fn get_receiver(&mut self) -> &mut sys::Receiver;
		/**
			* Received packs handler functions
			**/
		fn on_FirstPack(&mut self);

		/**
			* Translate received byte(s) into pack(s)
			**/
		#[inline(always)]
		fn bytes_into_packs(&mut self, src: &[u8]) -> Result<usize, ::std::io::Error> {
			unsafe {
				sys::receive_adv(src.as_ptr(), src.len(), self.get_receiver());
			}
			Ok(src.len() as usize)
		}
		/**
		 *Convenient  sys::Receiver constructor
		 **/
		fn new() -> sys::Receiver { sys::Receiver::new(Self::dispatch) }
		/**
			*Received packs to packs handler functions dispatcher
			**/
		unsafe extern "C" fn dispatch(receiver: *mut sys::Receiver, id: usize, pack: *mut sys::Pack) -> *const sys::Meta {
			let self_ = Self::into_self(receiver);
			match id {
				0 => {
					if pack.is_null() {
						return host::Client::FirstPack::meta_;
					}
					Self::on_FirstPack(self_);
				}

				_ => panic!("unknown ID"),
			}

			::std::ptr::null_mut()
		}
	}
}

use ADV_::IReceiver as ADV__IReceiver;
pub struct ADV__receiver {
	pub receiver: sys::Receiver,
}

impl ADV__receiver {
	pub fn new() -> ADV__receiver { ADV__receiver { receiver: <ADV__receiver as ADV_::IReceiver>::new() } }
}

impl ADV_::IReceiver for ADV__receiver {
	unsafe fn into_self<'a>(receiver: *mut sys::Receiver) -> &'a mut Self { ad_hoc_gen::sys::self_by_field_ptr!(receiver, receiver) }
	fn get_receiver(&mut self) -> &mut sys::Receiver { &mut self.receiver }
	fn on_FirstPack(&mut self) { println!("FirstPack") }
}
impl ::std::io::Write for ADV__receiver {
	#[inline(always)]
	fn write(&mut self, src: &[u8]) -> Result<usize, ::std::io::Error> { self.bytes_into_packs(src) }
	#[inline(always)]
	fn flush(&mut self) -> Result<(), ::std::io::Error> { Ok(()) }
}

fn on_FirstPack() {}

#[test]
fn it_works() -> ::std::io::Result<()> {
	use crate::demo;
	let buff = [0u8; 512];
	let mut curs = sys::Cursors::new();
	let mut tmp_curs = sys::Cursors::new();

	let mut ADV__r = ADV__receiver::new();
	let mut ClientServerLink_t = ClientServerLink_transmitter::new();
	if !ClientServerLink_t.send_FirstPack() {
		panic!("Send FirstPack error")
	}
	if ::std::io::copy(&mut ClientServerLink_t, &mut ADV__r).is_err() {
		panic!("cannot transmit data")
	}

	Ok(())
}
