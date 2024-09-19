const delete_btns = document.querySelectorAll('.delete')
const upadate_btns = document.querySelectorAll('.update')

handleClick =  async (event) => {
    id = event.target.value
    event.target.disabled = true
    data = await send_request(id, 'delete')
    if (data.success) {
        remove_element(id)
        createNotice(3000, 'success', data.success)
    }
    else {
        createElement(3000, 'error', data.error)
    }
    event.target.disabled = false
}

handleUpdate = async (event) => {
    id = event.target.value
    form_field(id)

}
delete_btns.forEach(delete_btn => {delete_btn.addEventListener('click', handleClick)})
upadate_btns.forEach(delete_btn => {delete_btn.addEventListener('click', handleUpdate)})

function form_field(id) {
    const tr = document.getElementById(`tr-${id}`)
    const oldTr = tr.innerHTML
    const oldHtml = tr.innerHTML
    let template = `<td><input required name="name" placeholder="Name" type="text" id='name'></td>
    <td><div>
        <input required name="month" placeholder="Month" type="number" min="1" max="12" id='month'><span>/</span>
        <input required id='day' name="day" placeholder="Day" type="number" min="1" max="31">
    </div></td>
    <td><button id="cancel">Cancel</button><button id="save">Save</button></td>`
    tr.innerHTML = template
    const cancel_btn = document.getElementById('cancel')
    cancel_btn.addEventListener('click', ()=> {
        tr.innerHTML = oldHtml

        const delete_btn = document.getElementById(`btd-${id}`)
        delete_btn.addEventListener('click', handleClick)

        const update_btn = document.getElementById(`btu-${id}`)
        update_btn.addEventListener('click', handleUpdate)

    })
    const save_btn = document.getElementById('save')
    handleSave = async () => {
        const tr = document.getElementById(`tr-${id}`)
        const birth_name = document.getElementById("name").value
        const birth_month = document.getElementById("month").value
        const birth_day = document.getElementById("day").value

        if (!birth_day || !birth_month || !birth_name) {
            createNotice(3000, 'error', 'fill the form')
        }
        else {
            
            body = {
                name: birth_name,
                month: birth_month,
                day: birth_day
            }

            res = await send_request(id, 'update', body)
            console.log(res)
            if (res.success) {
                let updated_tr = `
                <tr id="tr-${id}">
                    <td>${birth_name}</td>
                    <td>${birth_month}/${birth_day}</td>
                    <td><button class="delete" value="${id}" id="btd-${id}">Delete</button><button value="${id}" class="update" id="btu-${id}">Update</button></td>
                </tr>
                `
                tr.innerHTML = updated_tr

                createNotice(3000, 'success', res.success)
            }
            
            else {
                tr.innerHTML = oldTr
                createNotice(3000, 'error', res.error)
            }
            
            const delete_btn = document.getElementById(`btd-${id}`)
            delete_btn.addEventListener('click', handleClick)
    
            const update_btn = document.getElementById(`btu-${id}`)
            update_btn.addEventListener('click', handleUpdate)
    
        }
    }


    save_btn.addEventListener('click', handleSave)

}

function createNotice(time, mode, message) {
    const notice = document.createElement('div')
    notice.className = `animation ${mode}`
    notice.innerHTML = `<h3>${message}</h3>`
    document.body.appendChild(notice)

    setTimeout(()=> {
        document.body.removeChild(notice)
    }, time)
}


async function send_request(id, endpoint, body) {
res = await fetch(`http://localhost:5000/${endpoint}`, {
            method: 'POST',
            headers: {
                'content-type': 'application/json'
            },
            body: JSON.stringify({
                id: id,
                ...body,
            })
        })
    data = await res.json()
    return data
}

function remove_element(id) {
    const remove_element =  document.getElementById(`tr-${id}`)
    remove_element.remove()
}

