use crate::core::error::{Error, Result};

pub trait Operations {
    fn get_file_url(&self, board: &str) -> Result<String>;
}
