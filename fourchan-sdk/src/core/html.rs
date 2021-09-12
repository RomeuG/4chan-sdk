use html5ever::tendril::fmt::UTF8;
use html5ever::tendril::Tendril;
use html5ever::QualName;
use select::document::Document;
use select::node::{Data, Raw};

#[derive(Debug)]
pub enum TextType {
    PlainText(String),
    Italics(String),
    Link(String, Option<String>),
    Quote(String),
    NewLine,
}

pub(crate) fn html_get_property_value(
    property: &str,
    properties: &Vec<(QualName, Tendril<UTF8>)>,
) -> Option<String> {
    for prop in properties {
        if &prop.0.local == property {
            return Some(prop.1.to_string());
        }
    }

    return None;
}

pub fn html_parse_node(document: &Document, node: &Raw) -> Vec<TextType> {
    let mut vec: Vec<TextType> = vec![];

    if let Some(sibling_index) = node.first_child {
        let mut _sibling = document.nodes.get(sibling_index);

        while let Some(sibling) = _sibling {
            match &sibling.data {
                Data::Text(t) => match &node.data {
                    Data::Element(parent_qual, props) => {
                        if &parent_qual.local == "i" {
                            vec.push(TextType::Italics(t.to_string()));
                        } else if &parent_qual.local == "a" {
                            let href: Option<String> = html_get_property_value("href", &props);
                            vec.push(TextType::Link(t.to_string(), href));
                        } else if &parent_qual.local == "span" {
                            vec.push(TextType::Quote(t.to_string()));
                        } else {
                            vec.push(TextType::PlainText(t.to_string()));
                        }
                    }
                    _ => {
                        vec.push(TextType::PlainText(t.to_string()));
                    }
                },
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

pub fn html_parse_post(text: &str) -> Vec<TextType> {
    let document = Document::from(text);

    // for item in &document.nodes {
    //     println!("{:?}", item);
    // }

    let body_node = document.nodes.get(2).unwrap();
    let vec_text = html_parse_node(&document, body_node);

    // for text in vec_text {
    //     println!("{:?}", text);
    // }

    return vec_text;
}
