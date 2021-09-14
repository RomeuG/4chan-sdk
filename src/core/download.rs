use crate::core::utils;

use std::{fs, io::Write};

pub fn download_image(board: &str, tim: i64, extension: &str, dir: &std::path::Path) {
    let url = utils::create_media_url(board, tim, extension);

    if !dir.exists() {
        fs::create_dir(dir).expect("Could not create directory.")
    }

    let absolute_path = utils::create_media_path(dir, tim, extension);
    let bytes = reqwest::blocking::get(url).unwrap().bytes().unwrap();

    let mut file = fs::File::create(absolute_path).unwrap();
    file.write_all(&bytes.to_vec());
}
