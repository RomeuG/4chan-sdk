use crate::core::error::{Error, Result};
use crate::core::utils;

use std::{fs, io::Write};

///
/// Download image from specific board, with a specific extension to a chosen directory.
///
/// # Errors
///
/// Returns [`RequestError`](Error::RequestError) if the request returned an error.
///
/// Returns [`IoError`](Error::IoError) if any file operation failed.
///
/// # Examples
///
/// ```
/// download_image("g", 65436543, ".jpg", "/home/user/images");
/// ```
///
pub fn download_image(board: &str, tim: i64, extension: &str, dir: &std::path::Path) -> Result<()> {
    let url = utils::create_media_url(board, tim, extension);

    if !dir.exists() {
        fs::create_dir(dir).map_err(Error::IoError)?;
    }

    let absolute_path = utils::create_media_path(dir, tim, extension)?;
    let bytes = reqwest::blocking::get(url)
        .map_err(Error::RequestError)?
        .bytes()
        .map_err(Error::RequestError)?;

    let mut file = fs::File::create(absolute_path).map_err(Error::IoError)?;
    file.write_all(&bytes.to_vec()).map_err(Error::IoError)?;

    Ok(())
}
