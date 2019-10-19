[@react.component]
let make = (~iconSize, ~color, ~background, ~_IconComponent) =>
  ReasonReact.cloneElement(
    <RNHeaderButtons.HeaderButton
      _IconComponent=Icons.Ionicons.make
      iconSize=23.
      color=Constants.Colors.primaryColor
    />,
    ~props={
      "iconSize": iconSize,
      "color": color,
      "background": background,
      "IconComponent": _IconComponent,
    },
    [||],
  );