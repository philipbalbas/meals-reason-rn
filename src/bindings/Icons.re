module Ionicons = {
  [@bs.module "@expo/vector-icons"] [@react.component]
  external make:
    (~name: string, ~size: float=?, ~color: string=?) => React.element =
    "Ionicons";
};