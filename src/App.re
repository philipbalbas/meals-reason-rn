open ReactNative;
open Expo;

let fetchFonts = () =>
  Font.loadAsync([
    ("open-sans", Packager.require("../assets/fonts/OpenSans-Regular.ttf")),
    (
      "open-sans-bold",
      Packager.require("../assets/fonts/OpenSans-Bold.ttf"),
    ),
  ]);

[@react.component]
let app = () => {
  let (appLoaded, setAppLoaded) = React.useState(() => false);
  appLoaded
    ? <MealsNavigator />
    : <AppLoading
        startAsync=fetchFonts
        onFinish={() => setAppLoaded(_ => true)}
      />;
};