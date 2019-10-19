open ReactNative;
open Models;

let str = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "mealItem":
        style(
          ~height=200.->dp,
          ~width=100.->pct,
          ~backgroundColor="#f5f5f5",
          ~borderRadius=10.,
          ~overflow=`hidden,
          ~marginVertical=10.->dp,
          (),
        ),
      "bgImage":
        style(
          ~height=100.->pct,
          ~width=100.->pct,
          ~justifyContent=`flexEnd,
          (),
        ),
      "mealRow": style(~flexDirection=`row, ()),
      "mealHeader": style(~height=85.->pct, ()),
      "mealDetail":
        style(
          ~paddingHorizontal=10.->dp,
          ~justifyContent=`spaceBetween,
          ~alignItems=`center,
          ~height=15.->pct,
          (),
        ),
      "titleContainer":
        style(
          ~backgroundColor="rgba(0,0,0,0.5)",
          ~paddingVertical=5.->dp,
          ~paddingHorizontal=12.->dp,
          (),
        ),
      "title":
        style(
          ~fontFamily="open-sans-bold",
          ~fontSize=20.,
          ~color="white",
          ~textAlign=`center,
          (),
        ),
    })
  );

[@react.component]
let make = (~item, ~onSelectMeal) => {
  let duration = item.duration->string_of_int;
  <View style=styles##mealItem>
    <TouchableOpacity onPress=onSelectMeal>
      <View>
        <View
          style={StyleSheet.flatten([|styles##mealRow, styles##mealHeader|])}>
          <ImageBackground
            source={
              Image.uriSource(~uri=item.imageUrl, ())
              ->Image.Source.fromUriSource
            }
            style=styles##bgImage>
            <View style=styles##titleContainer>
              <Text style=styles##title numberOfLines=1>
                item.title->React.string
              </Text>
            </View>
          </ImageBackground>
        </View>
        <View
          style={StyleSheet.flatten([|styles##mealRow, styles##mealDetail|])}>
          <Text> {j|$duration m|j}->str </Text>
          <Text>
            {item.complexity->complexityToJs->String.uppercase->str}
          </Text>
          <Text>
            {item.affordability->affordabilityToJs->String.uppercase->str}
          </Text>
        </View>
      </View>
    </TouchableOpacity>
  </View>;
};