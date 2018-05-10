
# react-native-paytmpay
This library has been forked from https://github.com/elanic-tech/react-native-paytm
Updated it to work with the latest version of react-native and latest PayTM SDK. Improved the documentaion as well.

## Getting started

Alert: Built and tested  for iOS and android.

### installation

#### Android
````bash
react-native link react-native-paytmpay
````

#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-paytmpay` and add `RNPayTm.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNPayTm.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<
      

## Usage
```javascript
import paytm from 'react-native-paytmpay';
import { ..., NativeEventEmitter, ... } from 'react-native';

....

// Daat received from PayTM
constructer(props)
{
      this.myModuleEvt = new NativeEventEmitter(paytm);

}
 paytmErrorHandlerInIOS = (response) => {
    const responseObject = JSON.parse(response.response);
    const code = responseObject.RESPCODE.substring(0, 3);
    let payTmResponseMSG = ""
    if (code === "141") {
      payTmResponseMSG = "Transaction cancelled";
    } else {
      payTmResponseMSG = responseObject && responseObject.RESPMSG ? responseObject.RESPMSG : "";
    }

    setTimeout(() => {
      Alert.alert(
        "Transactions failed",
        payTmResponseMSG,
        [
          {
            text: "ok",
            onPress: () => { }
          }
        ],
        { cancelable: false }
      );
    }, 200);
  }


onPayTmResponse = (response) => {
    if (response.status && response.status === "Failed") {
      if (response.errorType && response.errorType) {
        setTimeout(() => {
          Alert.alert(
            "Transactions failed",
            response.errorType,
            [
              {
                text: "Ok",
                onPress: () => { }
              }
            ],
            { cancelable: false }
          );
        }, 200);
      } else {
        this.paytmErrorHandlerInIOS(response)
      }
    } else {
      let responseParseObject = null;
      if (Platform.OS === 'ios') {
        const responseObject = JSON.parse(response.response);
        if (responseObject.STATUS === "TXN_FAILURE") {
          this.paytmErrorHandlerInIOS(response)
        } else {
          responseParseObject = JSON.parse(response.response);
          if (responseParseObject.RESPCODE && responseParseObject.RESPCODE === "01") {
            //success
           
          }
        }
      } else {
        if (response.STATUS === "TXN_FAILURE") {
          //  const responseObject = response; 
          const code = response.RESPCODE.substring(0, 3);
          //let response = "";
          if (code === "141") {
            payTmResponseMSG = "Transaction cancelled";
          } else {
            payTmResponseMSG = response && response.RESPMSG ? response.RESPMSG : "";
          }

          setTimeout(() => {
            Alert.alert(
              "Transactions failed",
              payTmResponseMSG,
              [
                {
                  text: "ok",
                  onPress: () => { }
                }
              ],
              { cancelable: false }
            );
          }, 200);

        } else {
          responseParseObject = response;
          if (responseParseObject.RESPCODE && responseParseObject.RESPCODE === "01") {
            //success
          }
        }

      }


    }
  }
componentWillMount(){
    ...
   componentWillMount() {
    if (Platform.OS === "ios") {
      this.myModuleEvt.addListener("PayTMResponse", this.onPayTmResponse);
    } else {
      DeviceEventEmitter.addListener("PayTMResponse", this.onPayTmResponse);
    }
    ...
}



componentWillUnmount() {

    if (Platform.OS == "ios") {
      this.myModuleEvt.removeListener("PayTMResponse", this.onPayTmResponse);
    } else {
      DeviceEventEmitter.removeListener("PayTMResponse", this.onPayTmResponse);
    }
}

runTransaction() {
  //  const callbackUrl = `${paytmConfig.CALLBACK_URL}${orderId}`;
  const paytmConfig = {
            mid: MID,
            industryType: INDUSTRY_TYPE_ID,
            website: WEBSITE,
            channel: CHANNEL_ID,
            amount: TXN_AMOUNT,
            orderId: ORDER_ID,
            requestType: REQUEST_TYPE,
            custId: CUST_ID,
            callback: CALLBACK_URL,
            checksumhash: CHECKSUMHASH,
            ssoToken: SSO_TOKEN,
}
    paytm.startPayment(paytmConfig);
}
```
  
