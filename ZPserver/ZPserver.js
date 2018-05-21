var http = require('http');
var url = require('url');
var fs = require('fs');
var nodemailer = require('nodemailer');



http.createServer(function (req, res) {
  var q = url.parse(req.url, true);
  var qdata = q.query;
  if(qdata.state == "sign_up")
  {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(sign_up(qdata));
    res.end();
  }
  else {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write("fuck you");
    res.end();
  }
}).listen(8080);


function sign_up (qdata){

    if(!qdata.Email || 0 === qdata.Email.length || !qdata.ID || 0 === qdata.ID.length || !qdata.Pass || 4 >= qdata.Pass.length)
    {
      return 'incomplete';
    }
    var response;
    var rawdata = fs.readFileSync('Users.json');
    var m_users = JSON.parse(rawdata);
    var exist = false;
    m_users.users.forEach( function(element, index) {
        // statements
        if(qdata.Email == element.Email)
        {
          exist = true;
          //res.write("exist Email");
          response = 'existEmail';
        }
        if(qdata.ID == element.ID)
        {
          if(!exist){
            //res.write("exist ID");
            response = 'existID';
          }
          if(exist){
            //res.write(":ID");
            response = 'existBoth'
          }
          exist = true;

        }
    });
    if(exist)
    {
      //return res.end();
      return response;
    }
      if(!exist)
      {
        var verify_code = verification(qdata.Email);
        if(verify_code == "verifyMailErr")
        {
          return verify_code;
        }
        m_users["users"].push({"ID": qdata.ID, "Email": qdata.Email, "Pass": qdata.Pass, "code": verify_code, "veryfied": "NO"});//TODO: uncommet email
        rawdata = JSON.stringify(m_users);
        fs.writeFile("Users.json", rawdata, function(err)  {
        if (err) {
            console.log(err);
          }
        });
        //return res.end("user created");
        response = 'Veryfying';
        return response;
      }
}


var verification = function (email)
{
  var code = Math.floor(Math.random() * 9000) + 1000;
  var transporter = nodemailer.createTransport({
  service: 'gmail',
  auth: {
      user: 'kian.behzad@gmail.com',
      pass: 'STREET11'
    }
  });


  var mailOptions = {
    from: 'kian.behzad@gmail.com',
    to: email,
    subject: 'Verification code for Zprava',
    text: 'your code is ' + code.toString()
  };
  transporter.sendMail(mailOptions, function(error, info){
    if (error) {
      console.log("Something went wrong in sending verification code, please uncomment the code to see the full error message");
      //console.log(error);TODO: if you want a full error
    }
    else {
      console.log('Email sent: ' + info.response);
    }
  });
  return code;

}

