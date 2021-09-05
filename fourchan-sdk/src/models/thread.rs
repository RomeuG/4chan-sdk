use serde::{Deserialize, Serialize};

use crate::models::post::Post;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Thread {
    pub posts: Vec<Post>,
}
