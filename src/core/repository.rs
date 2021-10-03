use crate::models::board::Boards;
use crate::models::catalog::Catalog;
use crate::models::thread::Thread;

use crate::core::utils;

use crate::core::error::{Error, Result};

pub fn get_boards() -> Result<Boards> {
    let url = utils::url_builder_boards();

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().map_err(Error::RequestError)?;
    let boards = result.json::<Boards>().map_err(Error::ParseError)?;

    Ok(boards)
}

pub fn get_boards_json() -> Result<String> {
    let url = utils::url_builder_boards();

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().map_err(Error::RequestError)?;
    let json = result.text().map_err(Error::ParseError)?;

    Ok(json)
}

pub fn get_catalog(board: &str) -> Result<Catalog> {
    let url = utils::url_builder_catalog(board);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().map_err(Error::RequestError)?;
    let catalog = result.json::<Catalog>().map_err(Error::ParseError)?;

    Ok(catalog)
}

pub fn get_catalog_json(board: &str) -> Result<String> {
    let url = utils::url_builder_catalog(board);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let json: serde_json::Value = result.json().map_err(Error::RequestError)?;
    let pretty_printed = serde_json::to_string_pretty(&json).map_err(Error::PrettyPrintError)?;

    Ok(pretty_printed)
}

pub fn get_thread(board: &str, thread: &str) -> Result<Thread> {
    let url = utils::url_builder_thread(board, thread);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().map_err(Error::RequestError)?;
    let thread = result.json::<Thread>().map_err(Error::ParseError)?;

    Ok(thread)
}

pub fn get_thread_json(board: &str, thread: &str) -> Result<String> {
    let url = utils::url_builder_thread(board, thread);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let json: serde_json::Value = result.json().map_err(Error::RequestError)?;
    let pretty_printed = serde_json::to_string_pretty(&json).map_err(Error::PrettyPrintError)?;

    Ok(pretty_printed)
}
