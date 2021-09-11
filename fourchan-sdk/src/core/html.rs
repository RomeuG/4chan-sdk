use select::document::Document;
use select::node::{Data, Raw};

#[derive(Debug)]
pub enum TextType {
    PlainText(String),
    Italics(String),
    Link(String),
    Quote(String),
    NewLine,
}

pub fn html_parse_node(document: &Document, node: &Raw) -> Vec<TextType> {
    let mut vec: Vec<TextType> = vec![];

    if let Some(sibling_index) = node.first_child {
        let mut _sibling = document.nodes.get(sibling_index);

        while let Some(sibling) = _sibling {
            match &sibling.data {
                Data::Text(t) => {
                    vec.push(TextType::PlainText(t.to_string()));
                }
                Data::Element(qual, _) => {
                    if &qual.local == "br" {
                        vec.push(TextType::NewLine);
                    } else if &qual.local == "p" {
                        vec.append(&mut html_parse_node(document, sibling));
                    } else if &qual.local == "i" {
                        vec.append(&mut html_parse_node(document, sibling));
                    } else if &qual.local == "a" {
                        vec.append(&mut html_parse_node(document, sibling));
                    } else if &qual.local == "span" {
                        vec.append(&mut html_parse_node(document, sibling));
                    }
                }
                Data::Comment(_) => {}
            }

            let next_sibling_index = sibling.next;
            if let Some(i) = next_sibling_index {
                _sibling = document.nodes.get(i);
            } else {
                _sibling = None;
            }
        }
    }

    return vec;
}

pub fn html_parse_post(text: &str) {
    let document = Document::from(text);
    for item in &document.nodes {
        println!("{:?}", item);
    }

    println!("\n\n\n\n");

    let body_node = document.nodes.get(2).unwrap();
    let vec_text = html_parse_node(&document, body_node);

    for text in vec_text {
        println!("{:?}", text);
    }
}
