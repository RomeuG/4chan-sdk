use crate::models::board::Boards;
use crate::models::catalog::Catalog;
use crate::models::thread::Thread;

use crate::core::utils;

use crate::core::error::{Error, Result};

///
/// Get 4chan boards information as `Boards`.
///
/// # Errors
///
/// Returns [`RequestError`](Error::RequestError) if the request returned an error.
///
/// Returns [`ParseError`](Error::ParseError) if the parsing operation has failed.
///
/// # Examples
///
/// ```
/// match get_boards() {
///     Ok(b) => { println!("{:?}", b); },
///     Err(e) => { println!("{:?}", e); },
/// }
/// ```
///
pub fn get_boards() -> Result<Boards> {
    let url = utils::url_builder_boards();

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().map_err(Error::RequestError)?;
    let boards = result.json::<Boards>().map_err(Error::ParseError)?;

    Ok(boards)
}

///
/// Get 4chan boards information in JSON format as `String`.
///
/// # Errors
///
/// Returns [`RequestError`](Error::RequestError) if the request returned an error.
///
/// Returns [`ParseError`](Error::ParseError) if the parsing operation has failed.
///
/// # Examples
///
/// ```
/// match get_boards_json() {
///     Ok(s) => { println!("{}", s); },
///     Err(e) => { println!("{:?}", e); },
/// }
/// ```
///
pub fn get_boards_json() -> Result<String> {
    let url = utils::url_builder_boards();

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().map_err(Error::RequestError)?;
    let json = result.text().map_err(Error::ParseError)?;

    Ok(json)
}

///
/// Get 4chan board catalog information as `Catalog`.
///
/// # Errors
///
/// Returns [`RequestError`](Error::RequestError) if the request returned an error.
///
/// Returns [`ParseError`](Error::ParseError) if the parsing operation has failed.
///
/// # Examples
///
/// ```
/// match get_catalog("g") {
///     Ok(c) => { println!("{:?}", c); },
///     Err(e) => { println!("{:?}", e); },
/// }
/// ```
///
pub fn get_catalog(board: &str) -> Result<Catalog> {
    let url = utils::url_builder_catalog(board);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().map_err(Error::RequestError)?;
    let catalog = result.json::<Catalog>().map_err(Error::ParseError)?;

    Ok(catalog)
}

///
/// Get 4chan board catalog information in JSON format as `String`.
///
/// # Errors
///
/// Returns [`RequestError`](Error::RequestError) if the request returned an error.
///
/// Returns [`ParseError`](Error::ParseError) if the parsing operation has failed.
///
/// # Examples
///
/// ```
/// match get_catalog_json("g") {
///     Ok(s) => { println!("{}", s); },
///     Err(e) => { println!("{:?}", e); },
/// }
/// ```
///
pub fn get_catalog_json(board: &str) -> Result<String> {
    let url = utils::url_builder_catalog(board);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let json: serde_json::Value = result.json().map_err(Error::RequestError)?;
    let pretty_printed = serde_json::to_string_pretty(&json).map_err(Error::PrettyPrintError)?;

    Ok(pretty_printed)
}

///
/// Get 4chan thread information as `Thread`.
///
/// # Errors
///
/// Returns [`RequestError`](Error::RequestError) if the request returned an error.
///
/// Returns [`ParseError`](Error::ParseError) if the parsing operation has failed.
///
/// # Examples
///
/// ```
/// match get_thread("g", "83704034") {
///     Ok(t) => { println!("{:?}", t); },
///     Err(e) => { println!("{:?}", e); },
/// }
/// ```
///
pub fn get_thread(board: &str, thread: &str) -> Result<Thread> {
    let url = utils::url_builder_thread(board, thread);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().map_err(Error::RequestError)?;
    let thread = result.json::<Thread>().map_err(Error::ParseError)?;

    Ok(thread)
}

///
/// Get 4chan thread information in JSON format as `String`.
///
/// # Errors
///
/// Returns [`RequestError`](Error::RequestError) if the request returned an error.
///
/// Returns [`ParseError`](Error::ParseError) if the parsing operation has failed.
///
/// # Examples
///
/// ```
/// match get_thread_json("g", "83704034") {
///     Ok(s) => { println!("{}", s); },
///     Err(e) => { println!("{:?}", e); },
/// }
/// ```
///
pub fn get_thread_json(board: &str, thread: &str) -> Result<String> {
    let url = utils::url_builder_thread(board, thread);

    let client = reqwest::blocking::Client::new();
    let result = client.get(url).send().unwrap();

    let json: serde_json::Value = result.json().map_err(Error::RequestError)?;
    let pretty_printed = serde_json::to_string_pretty(&json).map_err(Error::PrettyPrintError)?;

    Ok(pretty_printed)
}
