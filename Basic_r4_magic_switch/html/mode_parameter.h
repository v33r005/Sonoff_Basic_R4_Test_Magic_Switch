#pragma once

namespace Supla {
namespace Html {

class ModeParameter : public Supla::HtmlElement {
 public:
  ModeParameter() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint32_t value = 0; // default value
      sender->send("<div class=\"box\">"); //box begin
      cfg->getUInt32(SELECT_MODE, &value);
      // form-field BEGIN
      sender->send("<h3>Ustawienie przekaźnika</h3>");
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(SELECT_MODE, "Stan po utracie zasilania:");
      sender->send("<select");
      sender->sendNameAndId(SELECT_MODE);
      sender->send("onchange=\"modeToggle();\">");
      sender->send("<option value=\"0\"");
      sender->send(selected(value == 0));
      sender->send(">Wyłączony</option>");
      sender->send("<option value=\"1\"");
      sender->send(selected(value == 1));
      sender->send(">Załączony</option>");
      sender->send("<option value=\"2\"");
      sender->send(selected(value == 2));
      sender->send(">Przywróć Stan</option>");
      sender->send("</select>");
      sender->send("</div>");
      sender->send("</div>");

      sender->send("<div class=\"box\">"); //box begin
      sender->send("<h3>Opcje Magic Switch</h3>");
      uint8_t value2 = 0; // default 
      cfg->getUInt8(MAGIC_SWITCH_ON, &value2);
      sender->send("<div class=\"form-field right-checkbox\">");
      sender->sendLabelFor(MAGIC_SWITCH_ON, "Włącz opcję Magic Switch");
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(MAGIC_SWITCH_ON, &value2);
      sender->send(checked(value2));
      sender->sendNameAndId(MAGIC_SWITCH_ON);
      sender->send(" onclick=\"ShowHideMagicSwitchOption()\">");
      sender->send("<span class=\"slider\"></span>");
      sender->send("</span>");
      sender->send("</label>");
      sender->send("</div>");

      sender->send("<div id=\"hiddenMagicMenu\" style=\"display: "); 
      sender->send(displayed(MagicSwitchOn));

      // hidden menu
        // ---------- filter value field
        sender->send("<div class=\"form-field\">");
        sender->sendLabelFor(FILTER_KEY, "Filter value");
        sender->send("<input type=\"number\" min=\"800\" max=\"");
      //  if (filterLimitIsOn == 1) {
      //    sender->send(limit-margin);
      //  } else {
      //    sender->send(50000);
      //  }
        sender->send("\" step=\"10\" ");
        sender->sendNameAndId(FILTER_KEY);
        sender->send(" value=\"");
        inCfgValue = filter; // default value
        cfg->getUInt32(FILTER_KEY, &inCfgValue);
        sender->send(inCfgValue);
        sender->send("\">");
        sender->send("</div>");
        sender->send("</div>");



      sender->send("<script>"
        "function ShowHideMagicSwitchOption() {"
          "var dp_checkBox = document.getElementById(\"");
      sender->send(MAGIC_SWITCH_ON);
      sender->send("\");"
          "var dp_content = document.getElementById(\"hiddenMagicMenu\");"
          "var hidden_field = document.getElementById(\"hidden_");
      sender->send(MAGIC_SWITCH_ON);
      sender->send("\");"
          "if (dp_checkBox.checked == true) {"
            "dp_content.style.display = \"block\";"
            "hidden_field.value = \"on\";"
          "} else {"
            "dp_content.style.display = \"none\";"
            "hidden_field.value = \"off\";"
          "}"
        "}"
      "</script>");

      

    }
  }

  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg && strcmp(key, SELECT_MODE) == 0) {
      int inFormValue = stringToUInt(value);
      cfg->setUInt32(SELECT_MODE, inFormValue);
      selectMode = inFormValue;
      return true;
    }
    if (cfg && strcmp(key, MAGIC_SWITCH_ON) == 0) {
      checkboxFound_ = true;
      uint8_t inCfgValue = 0;  // default value
      cfg->getUInt8(MAGIC_SWITCH_ON, &inCfgValue);
      uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
      if (inFormValue != inCfgValue) {
        MagicSwitchOn = inFormValue;
        cfg->setUInt8(MAGIC_SWITCH_ON, inFormValue);
      }
      return true;
    }

    return false;    
  }
  void onProcessingEnd() {
    if (!checkboxFound_) {
      handleResponse(MAGIC_SWITCH_ON, "off");
    }
    checkboxFound_ = false;
  }

 protected:  
 // uint32_t inCfgValue;
  int32_t inCfgIntValue = 0;
  bool checkboxFound_ = false;
  bool checkboxFound_1 = false;
  uint8_t inCfgTagMS = 0;
  uint8_t inCfgTagDC = 0;
  uint8_t inCfgTagFL = 0;
  uint32_t inCfgValue = 0;

};  // ModeParameter

};  // namespace Html
};  // namespace Supla
