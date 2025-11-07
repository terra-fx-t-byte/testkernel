#![no_std]
#![no_main]

#[allow(unused)]
use core::panic::PanicInfo;



use talc::{Talck, Talc, ClaimOnOom, Span};

static mut ARENA: [u8; 50000] = [0; 50000];

/*#[global_allocator]
static ALLOCATOR: Talck<spin::Mutex<()>, ClaimOnOom> = Talc::new(unsafe {
    ClaimOnOom::new(Span::from_array(&mut ARENA))
}).lock();
*/
#[cfg(not(test))]
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}