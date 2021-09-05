use crate::models::board::Boards;
use crate::models::catalog::Catalog;
use crate::models::thread::Thread;
use crate::{FORMAT_JSON, TYPE_THREAD, URL_THREAD};

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

pub fn get_boards() -> Boards {
    let url = url_builder_boards();

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let boards = result.json::<Boards>().unwrap();
    boards
}

pub fn get_boards_json() -> String {
    let url = url_builder_boards();

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let json = result.text().unwrap();
    json
}

pub fn get_catalog(board: &str) -> Catalog {
    let url = url_builder_catalog(board);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let catalog = result.json::<Catalog>().unwrap();
    catalog
}

pub fn get_catalog_json(board: &str) -> String {
    let url = url_builder_catalog(board);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let json = result.text().unwrap();
    json
}

pub fn get_thread(board: &str, thread: &str) -> Thread {
    let url = url_builder_thread(board, thread);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let thread = result.json::<Thread>().unwrap();
    thread
}

pub fn get_thread_json(board: &str, thread: &str) -> String {
    let url = url_builder_thread(board, thread);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let json = result.text().unwrap();
    json
}
