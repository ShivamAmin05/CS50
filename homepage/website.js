function hello_name() {
  let name = document.querySelector("#user_input");
  let response = document.querySelector("#response");
  response.innerHTML =
    "Hello " +
    name.value +
    ", my name is Shivam Amin and this website is all about me!";
}
