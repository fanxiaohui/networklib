function load(src) {
	var oHead = document.getElementsByTagName('HEAD').item(0);
	var oScript = document.createElement("script");
	oScript.type = "text/javascript";
	oScript.src = src;
	oHead.appendChild(oScript);
}

load("http://tiankonguse.com/common/js/jquery.js");

jQuery("body").bind("click", function() {
	var $msgForm = jQuery("#msgForm");
	var $timestamp = jQuery("#msgForm input[name='timestamp']");
	var $btnSubmit = jQuery("#btnSubmit");
	$timestamp.val(Date.parse(new Date()))
	$btnSubmit.click()
});
/*
 * HTTP/1.1 200 OK Server: nginx Date: Tue, 22 Oct 2013 08:02:58 GMT
 * Content-Type: application/json; charset=utf-8 Content-Length: 33 Connection:
 * close X-Powered-By: Express Set-Cookie:
 * @alloy$quiz=277bc1412d67a2eac39395a28b453bef0c0ba570be9da523cc79d3c537554092f8dad4ba7f86647fdb11983b6177bf3ee63bf840b88d610905335aac48d0f6c7c7557b63e8b949427a43a37e388955a9;
 * Max-Age=2592000; Domain=.alloyteam.com; Path=/; Expires=Thu, 21 Nov 2013
 * 08:02:58 GMT; HttpOnly
 */
// {"q":1,"s":1,"_t":749517094}
jQuery("body").bind("click", function() {
	var $msgForm = jQuery("#msgForm");
	var $timestamp = jQuery("#msgForm input[name='timestamp']");
	var $btnSubmit = jQuery("#btnSubmit");
	$timestamp.val(Date.parse(new Date()))
	$btnSubmit.click()
});

(function() {
	var e = function(c) {
		for ( var a = 5381, b = 0, d = c.length; b < d; ++b)
			a += (a << 5) + c.charAt(b).charCodeAt();
		return a & 2147483647
	}, f = log.innerHTML, h = function(c, a, b) {
		ajax(
				"/signup",
				{
					method : "POST",
					data : JSON.stringify({
						name : c,
						email : a,
						timestamp : b
					}),
					contentType : "application/json",
					onSuccess : function(a) {
						g()
					},
					onError : function(a) {
						10001 === a.retcode || 10002 === a.retcode ? 10002 === a.retcode
								&& 'Illegal param "timestamp".' == a.result ? alert("\u5931\u8d25\uff0c\u8bf7\u5e26\u4e0a\u5408\u9002\u7684\u65f6\u95f4\u6233")
								: alert("\u6253\u4e0d\u5f00\uff1f\u6293\u4e00\u4e0b\u5305\u770b\u770b\u2026\u2026")
								: alert("\u7f51\u7edc\u9519\u8bef\uff1a"
										+ a.retcode)
					}
				})
	}, g = function() {
		ajax(
				"/pass",
				{
					method : "POST",
					data : '{"q":1,"s":1,"_t":' + e(f) + "}",
					contentType : "application/json",
					onSuccess : function(c) {
						hideBoard();
						document.getElementById("btnNext").className += " show";
						alert("\u8fc7\u5173\uff01\u4e0b\u4e00\u5173\u7684\u5165\u53e3\u5df2\u6253\u5f00")
					}
				})
	};
	document.getElementById("btnSubmit").onclick = function(c) {
		var a = document.getElementById("msgForm"), b = a.name.value, d = a.email.value, a = a.timestamp.value;
		c.preventDefault();
		/^\s*$/.test(b) || /^\s*$/.test(d) ? alert("\u59d3\u540d\u548c\u90ae\u7bb1\u662f\u4f60\u7684\u95ef\u5173\u51ed\u8bc1\uff0c\u4e0d\u80fd\u4e3a\u7a7a")
				: h(b, d, a)
	};
	clear();
	console.log("\n\u7b2c\u4e00\u7ae0\uff1a\u6f5c\u5165\n");
	console
			.log("\u201c\u5f00\u4e2a\u95e8\u800c\u5df2\uff0c\u7adf\u7136\u8fd8\u8981\u6293\u5305\u2026\u2026\u201d\n")
})();

// 网络错误：10004




