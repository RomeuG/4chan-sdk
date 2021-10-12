use fourchan_sdk::core::repository::get_catalog_json;

fn main() {
    let result = get_catalog_json("g");
    match result {
        Ok(c) => {
            println!("{:?}", c);
        }
        Err(e) => {
            println!("{}", e);
        }
    }
}
