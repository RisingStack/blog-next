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

type post = {
  excerpt: string,
}

let decodePost = (json) => {
  Json.Decode.{
    excerpt: json |> field("excerpt", string),
  }
}

type response = {
  meta: meta,
  posts: list(post),
}

let decodeResponse = (json: Js.Json.t) => {
  Json.Decode.{
    meta: json |> field("meta", decodeMeta),
    posts: json |> field("posts", list(decodePost)),
  };
};

type state = {
  posts: list(post),
};

type action =
  | PostsReady(list(post));

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) =>
  switch (action) {
  | PostsReady(posts) => {...state, posts }
  }, {posts: []});

  React.useEffect0(() => {
    ignore(
      Js.Promise.(
        Axios.get("https://blog.risingstack.com/ghost/api/v2/content/posts/?key=c52dc242d7a6bbff4c6d010a44")
        |> then_((response) => {
          let posts = decodeResponse(response##data).posts
          dispatch(PostsReady(posts));
          resolve(
            None
          )
        })
      )
    );
    None;
  });

  let posts = List.map((post) => 
    <li key={post.excerpt}>{ReasonReact.string(post.excerpt)}</li>
  , state.posts);

  <div>
    <h1>{ReasonReact.string("Welcome to the RisingStack blog")}</h1>
    <ul>
      {ReasonReact.array(Array.of_list(posts))}
    </ul>
  </div>;
};
