function addCircle(px, py) {
    var point = new BMap.Point(px, py);
    var circle = new BMap.Circle(point, 6000, {
        strokeColor: "red",
        strokeWeight: 5,
        strokeOpacity: 0.3
    });
    map.addOverlay(circle);
}

function addMarker(px, py) {
    var point = new BMap.Point(px, py);
}

function init() {
    if (typeof qt != undefined) {
        new QWebChannel(qt.webChannelTransport, function (channel) {
            //Qt 类交互对象
            context = channel.objects.context;
            //关联Qt 交互对象内的信号
            context.sendPositionSignal.connect(function (x, y) {
                addCircle(x, y);
            });

            context.jsCallBack("send data");
        });
    } else {
        alert("qt 对象获取失败");
    }
}

window.onload = init;