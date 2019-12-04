
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]
#![allow(unused_imports)]
#![feature(const_transmute)]
#[macro_use]
extern crate bitflags;

#[path = "util.rs"]
pub mod util_;
pub use ad_hoc_sys as sys;
pub mod org {
	pub mod company {
		pub mod some_namespace {

			pub mod Client {
				use std::str;
				use std::mem::transmute;
				use crate::util_;

				pub mod FirstPack {
					use super::*;
					use crate::sys;
					pub static meta_: &sys::Meta = unsafe { transmute(&crate::util_::meta0) };
				}
			}

			pub mod ClientServerLink {
				use crate::org::company::some_namespace::Client as packs;
				use crate::sys;
				use std::mem::transmute;

				pub trait ITransmitter {
					/**
						*Function that fetch next pack from sending queue to send it
						**/
					unsafe extern "C" fn dequeue(dst: *mut sys::Transmitter) -> *mut sys::Pack;
					/**
					 *Add pack to the sending queue
					 **/
					fn queue(&mut self, pack: *mut sys::Pack) -> Result<(), *mut sys::Pack>;
					/**
					 *  Get reference to transmitter by customer transmitter
					 **/
					fn get_transmitter(&mut self) -> &mut sys::Transmitter;
					#[inline(always)]
					fn send_FirstPack(&mut self) -> bool { self.queue(unsafe { transmute(&packs::FirstPack::meta_) }).is_ok() }

					/**
					 *Request to translate packs in sending queue into provided bytes buffer
					 **/
					#[inline(always)]
					fn packs_into_bytes(&mut self, dst: &mut [u8]) -> Result<usize, ::std::io::Error> { unsafe { Ok(sys::transmit_adv(self.get_transmitter(), dst.as_mut_ptr(), dst.len()) as usize) } }

					fn new() -> sys::Transmitter { sys::Transmitter::new(Self::dequeue) }
				}
			}
		}
	}
}
