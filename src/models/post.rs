use crate::core::error::{Error, Result};
use crate::traits::operations::Operations;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Post {
    pub no: i64,
    pub sticky: Option<i64>,
    pub closed: Option<i64>,
    pub now: String,
    pub name: Option<String>,
    pub com: Option<String>,
    pub filename: Option<String>,
    pub ext: Option<String>,
    pub w: Option<i64>,
    pub h: Option<i64>,
    #[serde(rename = "tn_w")]
    pub tn_w: Option<i64>,
    #[serde(rename = "tn_h")]
    pub tn_h: Option<i64>,
    pub tim: Option<i64>,
    pub time: i64,
    pub md5: Option<String>,
    pub fsize: Option<i64>,
    pub resto: i64,
    pub capcode: Option<String>,
    #[serde(rename = "semantic_url")]
    pub semantic_url: Option<String>,
    pub replies: Option<i64>,
    pub images: Option<i64>,
    #[serde(rename = "omitted_posts")]
    pub omitted_posts: Option<i64>,
    #[serde(rename = "omitted_images")]
    pub omitted_images: Option<i64>,
    #[serde(rename = "last_replies")]
    #[serde(default)]
    pub last_replies: Vec<Post>,
    #[serde(rename = "last_modified")]
    pub last_modified: Option<i64>,
    pub sub: Option<String>,
    pub bumplimit: Option<i64>,
    pub imagelimit: Option<i64>,
    pub filedeleted: Option<i64>,
    pub trip: Option<String>,
}

impl Operations for Post {
    fn get_file_url(&self, board: &str) -> Result<String> {
        let tim = match self.tim {
            Some(t) => t,
            None => {
                return Err(Error::UnexpectedError);
            }
        };

        let ext = match self.ext.as_deref() {
            Some(e) => e,
            None => {
                return Err(Error::UnexpectedError);
            }
        };

        return Ok(format!("http://i.4cdn.org/{}/{}{}", board, tim, ext));
    }
}
