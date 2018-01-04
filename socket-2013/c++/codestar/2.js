(function() {
    function r() {
        ajax("/pass", {
            method: "POST",
            data: '{"q":1,"s":2,"_t":' + s(t) + "}",
            contentType: "application/json",
            onSuccess: function() {
                hideBoard();
                document.getElementById("btnNext").className += " show";
                alert("\u8fc7\u5173\uff01\u4e0b\u4e00\u5173\u7684\u5165\u53e3\u5df2\u6253\u5f00")
            }
        })
    }

    function u() {
        var a = +new Date,
        b = 0;
        k = setInterval(function() {
            var e = Math.floor(( + new Date - a) / 1E3);
            if (b !== e) {
                b = e;
                300 <= b && clearTimeout(k);
                var e = 300 - b,
                c = Math.floor(e / 60),
                d = e % 60,
                f = document.getElementById("clock");
                f.innerHTML = (10 > c ? "0" + c: c) + ":" + (10 > d ? "0" + d: d);
                10 >= e && (f.className = "timeup");
                0 >= e && (alert("\u8f66\u95f4\u7206\u70b8\u4e86\uff0c\u4f60\u6302\u4e86\u2026\u2026"), location.reload())
            }
        },
        500)
    }
    function m() {
        h[1] && h[2] && (clearTimeout(k), r())
    }
    function s(a) {
        for (var b = 5381,
        e = 0,
        c = a.length; e < c; ++e) b += (b << 5) + a.charAt(e).charCodeAt();
        return b & 2147483647
    }
    var t = log.innerHTML,
    g = document.getElementById("container"),
    n = [],
    l = [],
    h = [];
    l[1] = "width:40px;height:60px;";
    l[2] = "width:0;height:0;border-width:20px 10px 20px 0;border-style:solid;";
    var p = [,
    function() {
        for (var a = !0,
        b = document.getElementById("model_1"), e = ["borderTopLeftRadius", "borderTopRightRadius", "borderBottomLeftRadius", "borderBottomRightRadius"], c = [], d, f = 0, g = e.length; f < g; f++) {
            d = b.style[e[f]];
            if (!d) {
                a = !1;
                break
            }
            d = d.split(" ");
            if (1 === d.length) if ( - 1 === d[0].indexOf("%")) {
                a = !1;
                break
            } else d[1] = d[0];
            c.push(d[0]);
            c.push(d[1])
        }
        if (a) {
            f = 0;
            for (g = c.length; f < g; f++) c[f] = -1 === c[f].indexOf("%") ? parseInt(c[f]) : parseInt(parseFloat(c[f]) * (f % 2 ? 60 : 40) / 100);
            f = 2;
            for (g = c.length; f < g; f++) if (c[f] !== c[f % 2]) {
                a = !1;
                break
            }
            a && 3 * c[0] !== 2 * c[1] && (a = !1)
        }
        h[1] = a;
        document.getElementById("right_1").style.visibility = a ? "visible": "hidden";
        a && m()
    }],
    v = pfx("transformOrigin"),
    w = pfx("transform");
    p[2] = function() {
    	//	
        for (var a = !0,
        b = document.getElementById("main"), e = ["borderRightColor", "borderTopColor", "borderBottomColor"], c = getComputedStyle(b), d = e.length; d--;) 
        if (d) {
            if ("transparent" !== c[e[d]] && "rgba(0,0,0,0)" !== c[e[d]].replace(/\s/g, "")) {
                a = !1;
                break
            }
        } else if ("rgb(0,0,0)" !== c[e[d]].replace(/\s/g, "")) {
            a = !1;
            break
        }
        a && ( - 1 === b.style[w].indexOf("rotate(-60deg)") ? a = !1 : (b = b.style[v], "top right" !== b && ((b = b.split(" ")) && b.length ? "top right" === b || "right top" === b || -1 !== " 10px 100% right ".indexOf(" " + b[0] + " ") && -1 !== " 0 0px 0% top ".indexOf(" " + b[1] + " ") || (a = !1) : a = !1)));
        //h[2] = a;
        console.log(a);
        //document.getElementById("right_2").style.visibility = a ? "visible": "hidden";
        //a && m()
    };
    var k;
    g.onkeyup = function(a) {
        a = a.target;
        var b = Number(a.id.slice(9));
        document.getElementById("model_" + b).style.cssText = n[b] + a.value + l[b];
        p[b]()
    };
    var q;
    on(document.getElementById("btnQuiz"), "click",
    function() {
        q || (q = !0, u())
    });
    for (g = 1; 2 >= g; g++) n[g] = document.getElementById("model_" + g).style.cssText;
    clear();
    console.log("\n\u7b2c\u4e8c\u7ae0\uff1a\u610f\u5916\n");
    console.log("\u201c\u54e5\u4eec\u662f\u4e0d\u662f\u6ce8\u5b9a\u8981\u62ef\u6551\u4e16\u754c\uff0c\u8fd9\u79cd\u4e8b\u4e5f\u88ab\u6211\u78b0\u4e0a = =");
    console.log("\u65cb\u8f6c\u539f\u70b9\uff0c\u90a3\u662f\u5de6\u4e0a\u65b9\u5427?...\u53c8\u597d\u50cf\u4e0d\u662f");
    console.log("\u597d\u50cf\u5728\u54ea\u770b\u8fc7\u8fd9\u4e2aCSS3\u4f01\u9e45\u2026\u2026\u201d\n")

}

)();


/*
border-radius:40px / 60px;
 * 
-webkit-transform-origin: top right; 
-webkit-transform: rotate(-60deg);
border-top: 20px solid transparent; 
border-bottom: 20px solid transparent;
border-right: 10px solid rgb(0,0,0);
 */
