#![allow(non_snake_case)]

use tools::*;

fn main() {
	if std::env::args().len() != 3 {
		eprintln!("Usage: {} <input> <output>", std::env::args().nth(0).unwrap());
		return;
	}
	let in_file = std::env::args().nth(1).unwrap();
	let out_file = std::env::args().nth(2).unwrap();
	let input = std::fs::read_to_string(&in_file).unwrap_or_else(|_| { eprintln!("no such file: {}", in_file); std::process::exit(1) });
	let output = std::fs::read_to_string(&out_file).unwrap_or_else(|_| { eprintln!("no such file: {}", out_file); std::process::exit(1) });
	let input = read_input_str(&input);
	let output = read_output_str(&input, &output);
	let (score, svg, err) = vis(&input, &output, false, !0, false);
	if err.len() > 0 {
		println!("{}", err);
	}
	println!("Score = {}", score);
	std::fs::write("out.svg", &svg).unwrap();
}
