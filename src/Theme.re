open Css;

let card = style([
  boxShadow(
    Shadow.box(
      ~y=px(0),
      ~x=pxFloat(0.5),
      ~blur=px(2),
      rgba(0, 0, 0, 0.2),
    )
  ),  
  backgroundColor(white),
  width(px(300)),
  marginBottom(px(30)),
]);

let posts = style([
  display(flexBox),
  justifyContent(spaceBetween),
  maxWidth(px(620)),
  marginTop(px(0)),
  marginBottom(px(0)),
  marginRight(auto),
  marginLeft(auto),
  flexWrap(wrap),
])