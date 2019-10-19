open ReactNative;
let str = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "gridItem":
        style(
          ~flex=1.,
          ~margin=15.->dp,
          ~height=150.->dp,
          ~borderRadius=10.,
          ~overflow={
            Platform.os == Platform.android ? `hidden : `visible;
          },
          ~elevation=5.,
          (),
        ),
      "container":
        style(
          ~flex=1.,
          ~borderRadius=10.,
          ~shadowColor="black",
          ~shadowOpacity=0.26,
          ~shadowOffset=offset(~width=0., ~height=0.),
          ~shadowRadius=10.,
          ~elevation=3.,
          ~padding=15.->dp,
          ~justifyContent=`flexEnd,
          ~alignItems=`flexEnd,
          (),
        ),
      "title":
        style(
          ~fontFamily="open-sans-bold",
          ~fontSize=20.,
          ~textAlign=`right,
          (),
        ),
    })
  );

module TouchableCmp = {
  let defaultStyle = Style.style(~flex=1., ());
  [@react.component]
  let make = (~onPress, ~children, ~style) => {
    let style = StyleSheet.flatten([|style, defaultStyle|]);
    Platform.os == Platform.android
      ? <View style>
          <TouchableNativeFeedback onPress> children </TouchableNativeFeedback>
        </View>
      : <TouchableOpacity style onPress> children </TouchableOpacity>;
  };
};

[@react.component]
let make = (~title, ~onSelect, ~color) => {
  <TouchableCmp style=styles##gridItem onPress=onSelect>
    <View
      style={StyleSheet.flatten([|
        styles##container,
        Style.style(~backgroundColor=color, ()),
      |])}>
      <Text style=styles##title> title->str </Text>
    </View>
  </TouchableCmp>;
};