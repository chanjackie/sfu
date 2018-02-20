var { URL } = require('url'); // URL is a contructor
var ad = new URL('http://localhost:8080/app.html?year=2018&month=February&day=4');


console.log('host:', ad.host);
console.log('origin:', ad.origin);
console.log('search:', ad.search);
console.log('pathname:', ad.pathname);
console.log('port:', ad.port);
console.log('searchParams:', ad.searchParams.get('year'));

ad.username = 'bobby';
ad.password = '12345';

console.log('ad:', ad.toString());
