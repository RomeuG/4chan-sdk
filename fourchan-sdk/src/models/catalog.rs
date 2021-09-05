use serde::{Deserialize, Serialize};

use crate::models::thread::Thread;

pub type Catalog = Vec<CatalogItem>;

#[derive(Serialize, Deserialize)]
pub struct CatalogItem {
    pub page: u32,
    pub threads: Vec<Thread>,
}
