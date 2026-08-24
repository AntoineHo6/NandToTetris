use std::collections::HashMap;

pub struct SymbolTable {
    table: HashMap<String, u16>,
}

impl SymbolTable {
    pub fn new() -> Self {
        Self {
            table: HashMap::new(),
        }
    }

    pub fn add_entry(&mut self, symbol: String, address: u16) {
        self.table.insert(symbol, address);
    }
}