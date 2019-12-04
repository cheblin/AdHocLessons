
use ad_hoc_sys as sys;

use std::str::from_utf8_unchecked_mut;
use std::slice::from_raw_parts_mut;
use std::mem::transmute;
use std::ptr::copy_nonoverlapping;
use crate::org::company::some_namespace as host;
use host::Client as packs;

#[repr(C)]
pub struct Meta0(pub u16, u32, u32, u32, u16, u32, pub u32, u16, [*const sys::Field; 0]);
unsafe impl std::marker::Sync for Meta0 {}
pub static meta0: Meta0 = Meta0(0, 0, 0, 0, 0, 0, 0, 0, []);
