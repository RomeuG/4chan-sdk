use std::path::Path;
use std::path::PathBuf;

use std::fs;

use crate::{FORMAT_JSON, TYPE_THREAD, URL_IMG, URL_THREAD};

fn get_absolute_path(path: &Path) -> &Path {
    if path.is_absolute() {
        return path;
    } else {
        let path_buf = PathBuf::from(path);
        return fs::canonicalize(path_buf).unwrap().as_path();
    }
}

#[inline(always)]
fn url_builder_boards() -> String {
    format!("{}{}{}", URL_THREAD, "boards", FORMAT_JSON)
}

#[inline(always)]
fn url_builder_catalog(board: &str) -> String {
    format!("{}{}{}{}", URL_THREAD, board, "/catalog", FORMAT_JSON)
}

#[inline(always)]
fn url_builder_thread(board: &str, thread: &str) -> String {
    format!(
        "{}{}{}{}{}",
        URL_THREAD, board, TYPE_THREAD, thread, FORMAT_JSON
    )
}

#[inline(always)]
pub fn create_media_url(board: &str, tim: i64, extension: &str) -> String {
    let file = format!("{}{}", tim, extension);
    format!("{}{}{}{}", URL_IMG, board, "/", file)
}

pub fn create_media_path<'a>(dir: &'a Path, tim: i64, extension: &str) -> &'a Path {
    let file = format!("{}{}", tim, extension);
    let absolute_path = get_absolute_path(dir);

    absolute_path.join(file).as_path()
}

pub fn create_media_path_f<'a>(dir: &'a Path, filename: &str, extension: &str) -> &'a Path {
    let file = format!("{}{}", filename, extension);
    let absolute_path = get_absolute_path(dir);

    absolute_path.join(file).as_path()
}
