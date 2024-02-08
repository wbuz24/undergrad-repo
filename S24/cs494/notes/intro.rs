use std::env::args; // args is stored in the env library 
use std::fs::File; // files
use std::io::{BufReader, Read, Result}; // traits - kind of like an interface 
use std::cmp::{min, max}; // takes two params & gives the min or max of the two
use std::thread::spawn;
use std::sync::mpsc::{channel, Receiver};

// i32: signed 32 bit integer
fn is_prime(val: i32) -> bool {
  val >= 2 && !(2..=((val as f64).sqrt() as i32).any(|x| val % x == 0))
}

fn main()
{
  
  let start = 2;
  let end = 200000;

  let mut receivers: Vec<Receiver<(i32, bool)>> = vec![];

  let mut i = start - 1;

  while i < end {
    let (sender, receiver) = channel();
    receivers.push_back(receiver);
    spawn(move || {
      for j in (i+1)..=min(end, i+5) {
        sender.send((j, is_prime(j))).unwrap();
      }
    });
    i = min(end, i+5);
  }

  i = 0;
  for k in receivers {
    while let Ok((num, isprime)) = k.recv() {
      if isprime {
        println!("{:6} ", num);
        i += 1;
        if i >= 15 {
          println!();
          i = 0;
        }
      }
    }
  }
  if i != 0 {
    println!();
  }

  // a is by default immutable - i.e. a cannot change
  //let a: Vec<String> = args().collect(); // a is a vector of strings collected from args 
  
  //if a.len() != 4 {
  //  println!("Usage: {} <from> <to> <file>", &a[0]);
  //  return;
  //}
  // ? indicates to print an error
  // let f = File::open(&mut a[3])?;
  // let br = BufReader::new(f);
  
}
