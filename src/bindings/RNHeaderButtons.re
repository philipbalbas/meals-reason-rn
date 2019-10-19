module HeaderButton = {
  [@bs.module "react-navigation-header-buttons"] [@react.component]
  external make:
    (
      ~_IconComponent: React.component(Js.t('a)),
      ~iconSize: float=?,
      ~color: string=?
    ) =>
    React.element =
    "HeaderButton";
};

module Item = {
  [@bs.module "react-navigation-header-buttons"] [@react.component]
  external make:
    (
      ~title: string,
      ~testId: string=?,
      ~color: string=?,
      ~onPress: _ => unit=?,
      ~show: [@bs.string] [ | `always | `never]=?,
      ~_ButtonElement: React.element=?,
      ~iconName: string=?,
      ~buttonStyle: ReactNative.Style.t=?,
      ~buttonWrapperStyle: ReactNative.Style.t=?
    ) =>
    React.element =
    "Item";
};

module HeaderButtons = {
  [@bs.module "react-navigation-header-buttons"] [@react.component]
  external make:
    (
      ~left: bool=?,
      ~_HeaderButtonComponent: React.component(Js.t('a)),
      ~children: React.element,
      ~overFlowButtonWrapperSteyle: ReactNative.Style.t=?,
      ~overFlowButtonTestID: string=?,
      ~_OverflowIcon: React.element=?
    ) =>
    React.element =
    "HeaderButtons";
};