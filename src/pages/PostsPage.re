type pagination = {
  limit: int,
  next: int,
  page: int,
  pages: int,
  total: int,
  prev: option(int)
}

let decodePagination = (json: Js.Json.t) => {
  Json.Decode.{
    limit: json |> field("limit", int),
    next: json |> field("next", int),
    page: json |> field("page", int),
    pages: json |> field("pages", int),
    total: json |> field("total", int),
    prev: json |> field("prev", optional(int)),
  }
}

type meta = {
  pagination: pagination,
}

let decodeMeta = (json) => {
  Json.Decode.{
    pagination: json |> field("pagination", decodePagination),
  }
}

let decodePost = (json): Types.post => {
  Json.Decode.{
    excerpt: json |> field("excerpt", string),
    id: json |> field("id", string),
  }
}

type response = {
  meta: meta,
  posts: list(Types.post),
}

let decodeResponse = (json: Js.Json.t) => {
  Json.Decode.{
    meta: json |> field("meta", decodeMeta),
    posts: json |> field("posts", list(decodePost)),
  };
};

type state = {
  posts: option(list(Types.post)),
};

type action =
  | PostsReady(option(list(Types.post)));

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) =>
  switch (action) {
  | PostsReady(posts) => { ...state, posts }
  }, {posts: None});

  React.useEffect0(() => {
    ignore(
      Js.Promise.(
        Axios.get("https://blog.risingstack.com/ghost/api/v2/content/posts/?key=c52dc242d7a6bbff4c6d010a44")
        |> then_((response) => {
          let posts = decodeResponse(response##data).posts
          dispatch(PostsReady(Some(posts)));
          resolve(
            None
          )
        })
      )
    );
    None;
  });


  <div>
    <h1>{ReasonReact.string("Welcome to the RisingStack blog")}</h1>
    {
      switch state.posts {
        | Some(posts) => 
          <Posts posts={posts} />
        | None => ReasonReact.string("Loading...") 
      }
    }
  </div>;
};
