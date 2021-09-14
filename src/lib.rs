#[macro_use]
extern crate lazy_static;

use std::collections::HashMap;

pub mod core;
pub mod models;

static URL_IMG: &str = "http://i.4cdn.org/";
static URL_THREAD: &str = "http://a.4cdn.org/";
static TYPE_THREAD: &str = "/thread/";
static FORMAT_JSON: &str = ".json";
static MEDIA: &str = "https://i.4cdn.org/{board}/{tim}/{file}";

lazy_static! {
    static ref CHAN_LIST: HashMap<&'static str, &'static str> = {
        let mut hm = HashMap::new();

        hm.insert("3", "https://boards.4channel.org/3/");
        hm.insert("a", "https://boards.4channel.org/a/");
        hm.insert("an", "https://boards.4channel.org/an/");
        hm.insert("aco", "https://boards.4chan.org/aco/");
        hm.insert("adv", "https://boards.4channel.org/adv/");
        hm.insert("asp", "https://boards.4channel.org/asp/");
        hm.insert("b", "https://boards.4chan.org/b/");
        hm.insert("bant", "https://boards.4chan.org/bant/");
        hm.insert("biz", "https://boards.4channel.org/biz/");
        hm.insert("c", "https://boards.4channel.org/c/");
        hm.insert("cgl", "https://boards.4channel.org/cgl/");
        hm.insert("ck", "https://boards.4channel.org/ck/");
        hm.insert("cm", "https://boards.4channel.org/cm/");
        hm.insert("co", "https://boards.4channel.org/co/");
        hm.insert("d", "https://boards.4chan.org/d/");
        hm.insert("diy", "https://boards.4channel.org/diy/");
        hm.insert("e", "https://boards.4chan.org/e/");
        hm.insert("f", "https://boards.4chan.org/f/");
        hm.insert("fa", "https://boards.4channel.org/fa/");
        hm.insert("fit", "https://boards.4channel.org/fit/");
        hm.insert("g", "https://boards.4channel.org/g/");
        hm.insert("gd", "https://boards.4channel.org/gd/");
        hm.insert("gif", "https://boards.4chan.org/gif/");
        hm.insert("h", "https://boards.4chan.org/h/");
        hm.insert("hc", "https://boards.4chan.org/hc/");
        hm.insert("hm", "https://boards.4chan.org/hm/");
        hm.insert("hr", "https://boards.4chan.org/hr/");
        hm.insert("his", "https://boards.4channel.org/his/");
        hm.insert("i", "https://boards.4chan.org/i/");
        hm.insert("ic", "https://boards.4chan.org/ic/");
        hm.insert("int", "https://boards.4channel.org/int/");
        hm.insert("jp", "https://boards.4channel.org/jp/");
        hm.insert("k", "https://boards.4channel.org/k/");
        hm.insert("lgbt", "https://boards.4channel.org/lgbt/");
        hm.insert("lit", "https://boards.4channel.org/lit/");
        hm.insert("m", "https://boards.4channel.org/m/");
        hm.insert("mu", "https://boards.4channel.org/mu/");
        hm.insert("mlp", "https://boards.4channel.org/mlp/");
        hm.insert("n", "https://boards.4channel.org/n/");
        hm.insert("news", "https://boards.4channel.org/news/");
        hm.insert("o", "https://boards.4channel.org/o/");
        hm.insert("out", "https://boards.4channel.org/out/");
        hm.insert("p", "https://boards.4channel.org/p/");
        hm.insert("po", "https://boards.4channel.org/po/");
        hm.insert("pol", "https://boards.4chan.org/pol/");
        hm.insert("qst", "https://boards.4channel.org/qst/");
        hm.insert("r", "https://boards.4chan.org/r/");
        hm.insert("r9k", "https://boards.4chan.org/r9k/");
        hm.insert("s", "https://boards.4chan.org/s/");
        hm.insert("sp", "https://boards.4channel.org/sp/");
        hm.insert("s4s", "https://boards.4chan.org/s4s/");
        hm.insert("sci", "https://boards.4channel.org/sci/");
        hm.insert("soc", "https://boards.4chan.org/soc/");
        hm.insert("t", "https://boards.4chan.org/t/");
        hm.insert("tg", "https://boards.4channel.org/tg/");
        hm.insert("toy", "https://boards.4channel.org/toy/");
        hm.insert("trv", "https://boards.4channel.org/trv/");
        hm.insert("u", "https://boards.4chan.org/u/");
        hm.insert("v", "https://boards.4channel.org/v/");
        hm.insert("vg", "https://boards.4channel.org/vg/");
        hm.insert("vp", "https://boards.4channel.org/vp/");
        hm.insert("vr", "https://boards.4channel.org/vr/");
        hm.insert("vip", "https://boards.4channel.org/vip/");
        hm.insert("w", "https://boards.4channel.org/w/");
        hm.insert("wg", "https://boards.4chan.org/wg/");
        hm.insert("wsg", "https://boards.4channel.org/wsg/");
        hm.insert("wsr", "https://boards.4channel.org/wsr/");
        hm.insert("x", "https://boards.4channel.org/x/");
        hm.insert("y", "https://boards.4chan.org/y/");

        hm
    };
}
