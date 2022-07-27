function mcq(name)
{
    if(name == "peregrine falcon")
    {
        let button = document.getElementById(name)
        button.style.backgroundColor = '#53A76F'
        document.getElementById('result').innerHTML = 'Correct!';
    }
    else
    {
        const button = document.getElementById(name)
        document.getElementById('result').innerHTML = 'Incorrect';
        button.style.backgroundColor = '#D34040'
    }
}


function submit()
{
    var input = document.getElementById('submit')
    if(input.value.toLowerCase() == "cyan")
    {
        document.getElementById('result2').innerHTML = "Correct!";
        input.style.backgroundColor = '#53A76F'
    }
    else
    {
        document.getElementById('result2').innerHTML = "Incorrect";
        input.style.backgroundColor = '#D34040'
    }
}