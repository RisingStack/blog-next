[@react.component]
let make = (~post: Types.post) =>
  <div key={post.id} className=Theme.card>
    {ReasonReact.string(post.excerpt)}
  </div>