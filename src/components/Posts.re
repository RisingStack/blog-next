[@react.component]
let make = (~posts) =>
  <div className=Theme.posts>
    {ReasonReact.array(
      Array.of_list(
        posts |> List.map((post: Types.post) =>
          <Post post={post}/>
        ),
      ),
    )}
  </div>