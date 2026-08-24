use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead};

mod parser;



fn main() {
    let file_path = "Prog.asm";

    create_symbol_table(file_path);
}


fn create_symbol_table(file_path: &str) -> HashMap<String, u16>{
    let table: HashMap<String, u16> = HashMap::new();

    // Open the file in read-only mode
    let file = File::open(file_path).expect("Could not open file");
    let reader = io::BufReader::new(file);

    // First pass
    for line in reader.lines() {
        match line {
            Ok(text) => println!("{text}"),
            Err(e) => eprintln!("Error reading line: {e}"),
        }
    }

    return table;
}

mod parser {
    
}