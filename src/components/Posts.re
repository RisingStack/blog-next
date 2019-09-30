[@react.component]
let make = (~posts) =>
  <ul>
    {ReasonReact.array(
      Array.of_list(
        posts |> List.map((post: Types.post) =>
          <li key={post.excerpt}>{ReasonReact.string(post.excerpt)}</li>
        ),
      ),
    )}
  </ul>