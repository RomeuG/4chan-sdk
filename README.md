# 4chan-sdk

A 4Chan SDK in Rust to interface with its API.

## Example

``` rust
fn main() {
    let result = get_catalog_json("g");
    match result {
        Ok(c) => { println!("{:?}", c); },
        Err(e) => { println!("{}", e); },
    }
}
```
