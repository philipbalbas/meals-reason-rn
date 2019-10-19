open ReactNative;
open ReactNavigation;
open Models;

let str = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "screen":
        style(~flex=1., ~justifyContent=`center, ~alignItems=`center, ()),
      "image": style(~width=100.->pct, ~height=200.->dp, ()),
      "listItem":
        style(
          ~marginVertical=10.->dp,
          ~marginHorizontal=20.->dp,
          ~borderColor="#ccc",
          ~borderWidth=1.,
          ~padding=10.->dp,
          (),
        ),
      "details":
        style(
          ~flexDirection=`row,
          ~padding=15.->dp,
          ~justifyContent=`spaceAround,
          (),
        ),
      "title":
        style(
          ~fontFamily="open-sans-bold",
          ~fontSize=22.,
          ~textAlign=`center,
          (),
        ),
    })
  );

let getMeal = (navigation, p) => {
  navigation
  ->Navigation.getParam(p)
  ->Js.Nullable.toOption
  ->Belt.Option.flatMap(mealId =>
      DummyData.meals->Belt.Map.String.get(mealId)
    );
};

module ListItem = {
  [@react.component]
  let make = (~children) =>
    <View style=styles##listItem> <Text> children </Text> </View>;
};

[@react.component]
let make = (~navigation) => {
  let meal = navigation->getMeal("mealId");

  let ingredients =
    meal
    ->Belt.Option.mapWithDefault([||], m => m.ingredients)
    ->Belt.Array.map(ing => <ListItem key=ing> ing->str </ListItem>)
    ->React.array;
  let steps =
    meal
    ->Belt.Option.mapWithDefault([||], m => m.steps)
    ->Belt.Array.map(step => <ListItem key=step> step->str </ListItem>)
    ->React.array;
  let imageUrl = meal->Belt.Option.mapWithDefault("", m => m.imageUrl);
  let duration = meal->Belt.Option.mapWithDefault(0, m => m.duration);
  let complexity =
    meal->Belt.Option.mapWithDefault(`simple, m => m.complexity);
  let affordability =
    meal->Belt.Option.mapWithDefault(`affordable, m => m.affordability);

  <ScrollView>
    <Image
      source={Image.uriSource(~uri=imageUrl, ())->Image.Source.fromUriSource}
      style=styles##image
    />
    <View style=styles##details>
      <Text> {j|$duration m|j}->str </Text>
      <Text> {complexity->complexityToJs->String.uppercase->str} </Text>
      <Text> {affordability->affordabilityToJs->String.uppercase->str} </Text>
    </View>
    <Text style=styles##title> "Ingredients"->str </Text>
    ingredients
    <Text style=styles##title> "Steps"->str </Text>
    steps
  </ScrollView>;
};

make->NavigationOptions.setDynamicNavigationOptions(params =>
  NavigationOptions.t(
    ~title=
      params##navigation
      ->getMeal("mealId")
      ->Belt.Option.mapWithDefault("Missing", v => v.title),
    // TODO: Doesn't fucking work!!!!
    // <RNHeaderButtons.HeaderButtons _HeaderButtonComponent=HeaderButton.make>
    //   <RNHeaderButtons.Item title="favorite" iconName="ios-star" />
    // </RNHeaderButtons.HeaderButtons>,
    ~headerRight=
      <TouchableOpacity
        style=Style.(
          style(~width=24.->dp, ~margin=11.->dp, ~height=24.->dp, ())
        )>
        <Icons.Ionicons
          name="ios-star"
          color={
            Platform.os == Platform.android
              ? Constants.Colors.primaryColor : "#fff"
          }
          size=24.
        />
      </TouchableOpacity>,
    (),
  )
);