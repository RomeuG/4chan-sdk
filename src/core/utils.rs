use std::path::Path;
use std::path::PathBuf;

use std::fs;

use crate::core::error::{Error, Result};

use crate::{FORMAT_JSON, TYPE_THREAD, URL_IMG, URL_THREAD};

// NOTE: memory is being wasted here...
fn get_absolute_path(path: &Path) -> Result<PathBuf> {
    if path.is_absolute() {
        return Ok(path.to_path_buf());
    } else {
        let path_buf = PathBuf::from(path);
        return fs::canonicalize(path_buf).map_err(Error::IoError);
    }
}

#[inline(always)]
pub(crate) fn url_builder_boards() -> String {
    format!("{}{}{}", URL_THREAD, "boards", FORMAT_JSON)
}

#[inline(always)]
pub(crate) fn url_builder_catalog(board: &str) -> String {
    format!("{}{}{}{}", URL_THREAD, board, "/catalog", FORMAT_JSON)
}

#[inline(always)]
pub(crate) fn url_builder_thread(board: &str, thread: &str) -> String {
    format!(
        "{}{}{}{}{}",
        URL_THREAD, board, TYPE_THREAD, thread, FORMAT_JSON
    )
}

#[inline(always)]
pub(crate) fn create_media_url(board: &str, tim: i64, extension: &str) -> String {
    let file = format!("{}{}", tim, extension);
    format!("{}{}{}{}", URL_IMG, board, "/", file)
}

pub(crate) fn create_media_path(dir: &Path, tim: i64, extension: &str) -> Result<PathBuf> {
    let file = format!("{}{}", tim, extension);
    let absolute_path = get_absolute_path(dir)?;

    Ok(absolute_path.join(file))
}

pub(crate) fn create_media_path_f(dir: &Path, filename: &str, extension: &str) -> Result<PathBuf> {
    let file = format!("{}{}", filename, extension);
    let absolute_path = get_absolute_path(dir)?;

    Ok(absolute_path.join(file))
}
