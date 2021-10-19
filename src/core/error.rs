pub type Result<T> = std::result::Result<T, Error>;

#[derive(thiserror::Error, Debug)]
pub enum Error {
    #[error("Request error")]
    RequestError(#[source] reqwest::Error),

    #[error("Parsing error")]
    ParseError(#[source] reqwest::Error),

    #[error("HTML parsing error")]
    HtmlParseError,

    #[error("Pretty print error")]
    PrettyPrintError(#[source] serde_json::error::Error),

    #[error("IO error")]
    IoError(#[source] std::io::Error),

    #[error("Unexpected error")]
    UnexpectedError,
}
