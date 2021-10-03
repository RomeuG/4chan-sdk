pub type Result<T> = std::result::Result<T, Error>;

#[derive(thiserror::Error, Debug)]
pub enum Error {
    #[error("Request error")]
    RequestError(#[source] reqwest::Error),

    #[error("Parsing error")]
    ParseError(#[source] reqwest::Error),

    #[error("Pretty print error")]
    PrettyPrintError(#[source] serde_json::error::Error),

    #[error(transparent)]
    UnexpectedError(#[from] Box<dyn std::error::Error>),
}
